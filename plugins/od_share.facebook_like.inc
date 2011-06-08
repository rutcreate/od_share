<?php

/**
 * Return info.
 */
function od_share_facebook_like_info() {
  return array(
    'name' => t('Facebook Like'),
    'display callback' => 'od_share_facebook_like_display',
    'options callback' => 'od_share_facebook_like_options',
  );
}

/**
 * Return HTML.
 */
function od_share_facebook_like_display($vars) {
  foreach ($vars as $key => $value) {
    $$key = $value;
  }

  $output = '<iframe src="http://www.facebook.com/plugins/like.php?href='. $url .'&amp;send=false&amp;layout='. $option .'&amp;width=450&amp;show_faces=true&amp;action=like&amp;colorscheme=light&amp;font&amp;height=90" scrolling="no" frameborder="0" style="border:none; overflow:hidden; height:90px;" allowTransparency="true"></iframe>';
  //$output .= '<a name="fb_share" type="'. $option .'" share_url="'. $url .'"></a> <script src="http://static.ak.fbcdn.net/connect.php/js/FB.Share" type="text/javascript"></script>';
  return $output;
}

/**
 * Return options form.
 */
function od_share_facebook_like_options() {
  return array(
    'box_count' => t('Box Count'),
    'button_count' => t('Button Count'),
    'standard' => t('Standard'),
  );
}