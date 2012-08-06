<?php

/**
 * Return info.
 */
function od_share_facebookfbml_info() {
  return array(
    'name' => t('Facebook FBML'),
    'display callback' => 'od_share_facebookfbml_display',
    'options callback' => 'od_share_facebookfbml_options',
  );
}

/**
 * Return HTML.
 */
function od_share_facebookfbml_display($vars) {
  foreach ($vars as $key => $value) {
    $$key = $value;
  }
  $output = '<fb:share-button href="' . $url . '" type ="' . $option . '" ></fb:share-button>';
  return $output;
}

/**
 * Return options form.
 */
function od_share_facebookfbml_options() {
  return array(
    'box_count' => 'box_count',
    'button_count' => 'button_count',
    'button' => 'button',
    'icon_link' => 'icon_link',
    'icon' => 'icon',
  );
}