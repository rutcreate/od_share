<?php

/**
 * List page.
 */
function od_share_list() {
  $headers = array(
    t('Content type'),
    t('Edit'),
    t('Remove'),
  );

  $enabled = variable_get('od_share_enabled', array());
  $rows = array();
  foreach ($enabled as $type) {
    $name = node_get_types('name', array('type' => $type));
    $rows[] = array(
      l($name, 'admin/settings/od_share/'. $type),
      l(t('Edit'), 'admin/settings/od_share/'. $type),
      l(t('Remove'), 'admin/settings/od_share/'. $type .'/remove'),
    );
  }
  if ($rows) {
    $output = theme('table', $headers, $rows);
  }
  else {
    $output = t('No content type selected. Please choose content type <a href="!link">here</a>', array('!link' => url('admin/settings/od_share/ctypes')));
  }
  return $output;
}

/**
 * Content types settings.
 */
function od_share_ctypes() {
  // Options.
  $options= node_get_types('names');

  // Form.
  $form['od_share_ctypes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select content types'),
    '#description' => t(''),
    '#default_value' => variable_get('od_share_enabled', array()),
    '#options' => $options,
  );
  $form['od_share_config'] = array(
    '#type'  => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => t('OD Share global configuration settings'),
    '#tree'  => TRUE,
  );
  $form['od_share_config']['use_path_alias'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use path alias in stead of normal path.'),
    '#description' => t('Use drupal_get_path_alias instead.'),
    '#default_value' => variable_get('od_share_use_path_alias', FALSE),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  //$form['#redirect'] = 'admin/settings/od_share';
  return $form;
}

/**
 * Content types settings submit.
 */
function od_share_ctypes_submit($form, $form_state) {
  $ctypes = array_filter($form_state['values']['od_share_ctypes']);
  $use_path_alias_status = $form_state['values']['od_share_config']['use_path_alias'];
  $saved_num = count($form['form_id']['#post']['od_share_ctypes']);

  drupal_set_message($saved_num . ' '. t('content types') .' '. t('saved') . '.');
  variable_set('od_share_enabled', $ctypes);
  variable_set('od_share_use_path_alias', $use_path_alias_status);
}

/**
 * Edit plugins.
 */
function od_share_edit(&$form_state, $type = NULL, $view_use = FALSE) {
  // Check enabled content type.
  $enabled = variable_get('od_share_enabled', array());
  if (!in_array($type, $enabled) && !$view_use) {
    drupal_not_found();
    exit();
  }
  // Set title.
  if (!$view_use) {
    $name = node_get_types('name', array('type' => $type));
    drupal_set_title('Share button for '. $name);
  }

  // Generate form.
  $form['od_share']['#tree'] = TRUE;
  $plugins = od_share_get_plugins();
  // Get settings.
  if ($_info = od_share_get_type_info($type)) {
    $info = array();
    // Re-weight.
    $max_weight = -999;
    foreach ($_info as $i) {
      $info[$i['plugin']] = $i;
      // Set max weight
      if ($i['weight'] > $max_weight) $max_weight = $i['weight'];
    }
    // Make form in case of new plugins available.
    foreach ($plugins as $plugin) {
      // Make form.
      if ($i = $info[$plugin['plugin']]) {

        $plugin['enabled'] = $i['enabled'];
        $plugin['option_value'] = $i['options'];

        $form['od_share'][$i['weight']] = od_share_edit_fields($i['weight'], $plugin);
      }
      else {
        $max_weight++;
        $form['od_share'][$max_weight] = od_share_edit_fields($max_weight, $plugin);
      }
    }
  }
  // Make default.
  else {
    foreach ($plugins as $weight => $plugin) {
      $form['od_share'][$weight] = od_share_edit_fields($weight, $plugin);
    }
  }
  // Display position.
  $form['position'] = array(
    '#type' => 'radios',
    '#title' => t('Display position'),
    '#default_value' => variable_get('od_share_type_'. $type .'_position', 'link'),
    '#options' => array(
      'node' => t('Content by weight'),
      'link' => t('Link'),
    ),
  );
  $form['weight'] = array(
    '#type' => 'textfield',
    '#title' => t('Weight position'),
    '#description' => t('If above you select Content by weight, you need to enter weight.'),
    '#default_value' => variable_get('od_share_type_'. $type .'_weight', '0'),
    '#size' => 5,
  );
  $form['type'] = array(
    '#type' => 'hidden',
    '#value' => $type,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#suffix' => l(t('Back'), 'admin/settings/od_share'),
  );
  ksort($form['od_share']);
  return $form;
}
/**
 * Edit fields.
 */
function od_share_edit_fields($weight, $plugin) {
  $form['name'] = array(
    '#type' => 'markup',
    '#value' => $plugin['name'],
  );
  $form['description'] = array(
    '#type' => 'markup',
    '#value' => $plugin['description'],
  );
  $form['plugin'] = array(
    '#type' => 'hidden',
    '#value' => $plugin['plugin'],
  );
  $form['options'] = array(
    '#type' => 'select',
    '#options' => $plugin['options callback'](),
    '#default_value' => $plugin['option_value'],
  );
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#default_value' => $plugin['enabled'] ? $plugin['enabled'] : 0,
  );
  $form['weight'] = array(
    '#type' => 'weight',
    '#default_value' => $weight,
  );
  return $form;
}

/**
 * Edit submit.
 */
function od_share_edit_submit($form, $form_state) {
  $values = $form_state['values'];
  variable_set('od_share_type_'. $values['type'], $values['od_share']);
  variable_set('od_share_type_'. $values['type'] .'_position', $values['position']);
  variable_set('od_share_type_'. $values['type'] .'_weight', $values['weight']);
  drupal_set_message('The configuration options have been saved.');
}

/**
 * Remove setting form.
 */
function od_share_remove_confirm($form_state, $type) {
  $name = node_get_types('name', $type);
  $destination = isset($_GET['destination']) ? $_GET['destination'] : 'admin/settings/od_share';

  $form['type'] = array(
    '#type' => 'value',
    '#value' => $type,
  );
  $form['name'] = array(
    '#type' => 'value',
    '#value' => $name,
  );
  $form['#submit'] = array('od_share_remove_confirm_submit');

  $form = confirm_form($form,
    t('Are you sure you want to remove %name setting?', array('%name' => $name)),
    $destination,
    t('This action cannot be undone.'),
    t('Remove'),
    t('Cancel')
  );
  return $form;
}

/**
 * Remove settings form submit.
 */
function od_share_remove_confirm_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  $name = $form_state['values']['type'];

  // delete variables.
  variable_del('od_share_type_'. $type);
  variable_del('od_share_type_'. $type .'_position');
  variable_del('od_share_type_'. $type .'_weight');
  // edit enabled settings.
  $types = variable_get('od_share_enabled', array());
  unset($types[$type]);
  variable_set('od_share_enabled', $types);

  drupal_set_message('The %name configuration options have been removed.', array('%name' => $name));

  $form_state['redirect'] = isset($_GET['destination']) ? $_GET['destination'] : 'admin/settings/od_share';
}

/**
 * Facebook Application Settings.
 */

function od_share_facebook_app_settings() {
  $form['od_share_facebook_app_id'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('od_share_facebook_app_id', 'undefined'),
    '#description' => t('Facebook Application ID. ') .
                        l(
                           t('Get it here.'),
                           'http://developers.facebook.com/docs/reference/plugins/like/',
                           array('attributes' =>
                             array('target' => '_blank')
                           )
                         ),
    '#title' => t('App Id'),
  );
  $form['od_share_facebook_like_fbml_width'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('od_share_facebook_like_fbml_width', '450'),
    '#description' => t('Width in px.'),
    '#title' => t('Box Width'),
  );
  $form['od_share_facebook_use_send_button'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('od_share_facebook_use_send_button', FALSE),
    '#description' => t('Tick for show like and send button.'),
    '#title' => t('Use Send Button'),
  );
  $form['od_share_facebook_use_xfbml'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('od_share_facebook_use_xfbml', TRUE),
    '#description' => t('Description'),
    '#title' => t('Use FBML'),
  );
  return system_settings_form($form);
}
