<?php
// $Id$

/**
 * A handler to provide an OD Share field for a particular node.
 *
 * @ingroup views_field_handlers
 */
class od_share_handler_field_share extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['title'] = 'title';
    $this->additional_fields['type'] = 'type';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function option_definition() {
    $options = parent::option_definition();

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Remove the alteration stuff
    unset($form['alter']);
  }

  function render($values) {
    $node = new stdClass();
    $node->nid = $values->{$this->aliases['nid']};
    $node->title = $values->{$this->aliases['title']};
    $node->type = $values->{$this->aliases['type']};
    $output = od_share_get_buttons($node);
    return $output;
  }
}
