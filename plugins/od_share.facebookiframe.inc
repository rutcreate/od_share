<?php

/**
 * Return info.
 */
function od_share_facebookiframe_info() {
  return array(
    'name' => t('Facebook IFRAME'),
    'display callback' => 'od_share_facebookiframe_display',
    'options callback' => 'od_share_facebookiframe_options',
  );
}

/**
 * Return HTML.
 */
function od_share_facebookiframe_display($vars) {
  foreach ($vars as $key => $value) {
    $$key = $value;
  }
  $alias_url  = str_replace(':', '%3A', url($_GET['q'], array('absolute' => true)));
  $output = '<iframe id="gs_fb_sh" name="gs_fb_sh" scrolling="no" style="border: none; overflow: hidden; height: 59px; width: 54px; " class="fb_ltr " src="https://www.facebook.com/plugins/share_button.php?channel=http%3A%2F%2Fstatic.ak.facebook.com%2Fconnect%2Fxd_arbiter.php%3Fversion%3D9%23cb%3Df361332028%26relation%3Dparent.parent&href='. $alias_url  .'&locale=th_TH&sdk=joey&type='.$option .'" frameborder="0"></iframe>';
  return $output;
}

/**
 * Return options form.
 */
function od_share_facebookiframe_options() {
  return array(
    'box_count' => 'box_count',
    'button_count' => 'button_count',
    'button' => 'button',
    'icon_link' => 'icon_link',
    'icon' => 'icon',
  );
}