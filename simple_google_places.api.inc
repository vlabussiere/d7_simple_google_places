<?php
/**
 * @file
 * simple_google_places.api.inc
 */

/**
 * Implements hook_simple_google_places_alter_json_alter($json).
 */
function hook_simple_google_places_alter_json_alter($json) {
  $json->result->areaServed = 'FR';
}