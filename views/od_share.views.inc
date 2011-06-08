<?php

/**
 * Implementation of hook_views_data().
 */
function od_share_views_data() {
  $data['node']['od_share'] = array(
    'title' => t('OD Share'),
    'help' => t('Add share buttons, facebook, twitter, googlebuzz, print, etc.'),
    'field' => array(
      'handler' => 'od_share_handler_field_share',
    ),
  );
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function od_share_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'od_share') .'/views',
    ),
    'handlers' => array(
      'od_share_handler_field_share' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}
