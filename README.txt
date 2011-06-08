DESCRIPTION
-----------

This module allows you to add button share to anywhere you want in any node, 
buttons available are following below listed:

    * Facebook
    * Twitter
    * Google Buzz
    * Print, Print PDF, Send mail (Require print module)

INSTALLATION
------------

Follow the instructions in the provided INSTALL.txt file.

CONFIGURATION
-------------
  
  Administer > Site building > Modules (admin/build/modules)
    Enable or disable the module. (default: disabled)
  
  Administer > Site configuration > OD Share settings (admin/settings/od_share)
    This is where all the module-specific configuration options can be set.
  
- To display buttons, you have to add php code to node.tpl.php in your template folder:
<?php if ($od_share): ?>
  <div class="node-share"><?php print $od_share; ?></div>
<?php endif; ?>
