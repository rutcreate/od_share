<?php

/**
 * Return info.
 */
function od_share_html5like_info() {
  return array(
    'name' => t('Facebook Like (HTML5)'),
    'display callback' => 'od_share_html5like_display',
    'options callback' => 'od_share_html5like_options',
  );
}

/**
 * Return HTML.
 */
function od_share_html5like_display($vars) {
  foreach ($vars as $key => $value) {
    $$key = $value;
  }

  $alias_url  = url($_GET['q'], array('absolute' => true));
  $url = $alias_url; 
  $output = '<script src="http://static.ak.fbcdn.net/connect.php/js/FB.Share" type="text/javascript"> </script>';
  $appId = variable_get('od_share_facebook_app_id', '144611255587553');
$mystring = <<<EOT
  <div id="fb-root"></div>
  <script>(function(d, s, id) {
    var js, fjs = d.getElementsByTagName(s)[0];
    if (d.getElementById(id)) return;
    js = d.createElement(s); js.id = id;
    js.src = "//connect.facebook.net/en_GB/all.js#xfbml=1&appId=%s";
    fjs.parentNode.insertBefore(js, fjs);
  }(document, 'script', 'facebook-jssdk'));</script>
EOT;
  $output .= '<div class="fb-like" data-href="' .$url .'" data-send="false" data-width="450" data-show-faces="true" layout="'. $option .'"></div>';
  return $output;
}

/**
 * Return options form.
 */
function od_share_html5like_options() {
  return array(
    'box_count' => 'box_count',
    'button_count' => 'button_count',
    'button' => 'button',
    'icon_link' => 'icon_link',
    'icon' => 'icon',
  );
}