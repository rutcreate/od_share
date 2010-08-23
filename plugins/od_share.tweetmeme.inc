<?php

/**
 * Return info.
 */
function od_share_tweetmeme_info() {
  return array(
    'name' => t('Tweetmeme'),
    'display callback' => 'od_share_tweetmeme_display',
    'options callback' => 'od_share_tweetmeme_options',
  );
}

/**
 * Return HTML.
 */
function od_share_tweetmeme_display($vars) {
  foreach ($vars as $key => $value) {
    $$key = $value;
  }
  if ($option == 'compact') {
    $width = 70;
    $height = 30;
  }
  else {
    $width = 50;
    $height = 61;
  }
  $output = '<iframe scrolling="no" width="'. $width .'" height="'. $height .'" frameborder="0" src="http://api.tweetmeme.com/button.js?url='. $url .'&style='. $option .'"></iframe>';
  return $output;
}

/**
 * Return options form.
 */
function od_share_tweetmeme_options() {
  return array(
    'compact' => 'Compact',
    'normal' => 'Normal',
  );
}