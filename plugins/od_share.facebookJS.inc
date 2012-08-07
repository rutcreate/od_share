<?php

/**
 * Return info.
 */
function od_share_facebookJS_info() {
  return array(
    'name' => t('Facebook JS'),
    'display callback' => 'od_share_facebookJS_display',
    'options callback' => 'od_share_facebookJS_options',
  );
}

/**
 * Return HTML.
 */
function od_share_facebookJS_display($vars) {
  foreach ($vars as $key => $value) {
    $$key = $value;
  }

  $alias_url  = url($_GET['q'], array('absolute' => true));
  $url = $alias_url; 
  $output = '<script src="http://static.ak.fbcdn.net/connect.php/js/FB.Share" type="text/javascript"> </script>';
  $output .= '<a name="fb_share" type="'. $option .'" share_url="'. $url .'"></a>';
  return $output;
}

/**
 * Return options form.
 */
function od_share_facebookJS_options() {
  return array(
    'box_count' => 'box_count',
    'button_count' => 'button_count',
    'button' => 'button',
    'icon_link' => 'icon_link',
    'icon' => 'icon',
  );
}