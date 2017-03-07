<?php
/**
 * @file
 * Admin settings of simple_google_places module.
 */

/**
 * Form : admin/config/services/simple_google_places.
 */
function simple_google_places_menu_settings() {
  $form = [];
  $form['simple_google_places_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => variable_get('simple_google_places_api_key'),
    '#size' => 40,
    '#required' => TRUE,
  );
  $form['simple_google_places_limit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Limit allowed place ids?'),
    '#default_value' => variable_get('simple_google_places_limit'),
  );
  $form['simple_google_places_allowed_placeids'] = array(
    '#type' => 'textarea',
    '#title' => t('Place identifiers'),
    '#default_value' => variable_get('simple_google_places_allowed_placeids'),
    '#description' => t('One by line'),
    '#states' => [
      'visible' => [
        ':input[name="simple_google_places_limit"]' => array('checked' => TRUE),
      ],
    ],
  );
  $form['simple_google_places_log'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log errors?'),
    '#default_value' => variable_get('simple_google_places_log'),
  );
  return system_settings_form($form);
}
/**
 * Form validate : admin/config/services/simple_google_places.
 */
function simple_google_places_menu_settings_validate($form, &$form_state) {}