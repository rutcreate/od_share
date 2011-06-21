<?php

/**
 * Return info.
 */
function od_share_facebook_info() {
  return array(
    'name' => t('Facebook Share'),
    'display callback' => 'od_share_facebook_display',
    'options callback' => 'od_share_facebook_options',
  );
}

/**
 * Return HTML.
 */
function od_share_facebook_display($vars) {
  foreach ($vars as $key => $value) {
    $$key = $value;
  }

  $use_path_alias = variable_get('od_share_use_path_alias', FALSE);
  if ($use_path_alias) {
    $path_alias = drupal_get_path_alias($_GET['q']);
    $url = url($path_alias, array('absolute' => TRUE));
  }


  $use_xfbml = variable_get('od_share_facebook_use_xfbml', TRUE);
  $app_id = variable_get('od_share_facebook_app_id', 'undefined');

  if ($use_xfbml) {

    $output .= '<fb:share-button href="'. $url .'" type="'. $option .'"> </fb:share-button>';
  }
  else {
    $output .= '<a name="fb_share" type="'. $option .'" share_url="'. $url .'"></a> <script src="http://static.ak.fbcdn.net/connect.php/js/FB.Share" type="text/javascript"></script>';
  }
  return $output;
}

/**
 * Return options form.
 */
function od_share_facebook_options() {
  return array(
    'box_count' => t('Box Count'),
    'button_count' => t('Button Count'),
    'button' => t('Button'),
    'icon_link' => t('Icon Link'),
    'link' => t('Link'),
  );
}
