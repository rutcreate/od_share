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
  $output .= '<a name="fb_share" type="'. $option .'" share_url="'. $url .'"></a> <script src="http://static.ak.fbcdn.net/connect.php/js/FB.Share" type="text/javascript"></script>';
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
