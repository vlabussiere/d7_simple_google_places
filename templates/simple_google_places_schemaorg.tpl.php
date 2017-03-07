<?php
/**
 * @file
 * simple_google_places_schemaorg.tpl.php
 */
?>
<?php if (!empty($jsonld)) : ?>
<script type="application/ld+json">
  {
    "@type": "<?php echo (isset($jsonld->result->type)) ? $jsonld->result->type : 'Organization' ?>",
<?php if (isset($jsonld->result->website)) : ?>
    "url": "<?php echo check_plain($jsonld->result->website) ?>",
<?php endif; ?>
<?php if (isset($jsonld->result->international_phone_number)) : ?>
    "contactPoint" : [{
      "@type" : "ContactPoint",
      "telephone" : "<?php echo check_plain($jsonld->result->international_phone_number) ?>",
<?php if (isset($jsonld->result->contactType)) : ?>
      "contactType" : "<?php echo check_plain($jsonld->result->contactType) ?>",
<?php endif; ?>
<?php if (isset($jsonld->result->areaServed)) : ?>
      "areaServed" : "<?php echo check_plain($jsonld->result->areaServed) ?>",
<?php endif; ?>
    }]
<?php endif; ?>
  }
</script>
<?php endif; ?>