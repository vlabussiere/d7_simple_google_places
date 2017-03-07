<?php
/**
 * @file
 * simple_google_places.inc
 */

class SimpleGooglePlaces {

  const END_POINT = 'https://maps.googleapis.com/maps/api/place/details/json';

  /**
   * Get data from cache.
   *
   * @param string $place_id
   *   The place identifier.
   *
   * @return stdClass
   *   Json data.
   */
  public static function getData($place_id) {
    $data = cache_get('simple_google_places_' . $place_id);
    if (empty($data)) {
      $data = new stdClass();
      try {
        $data->data = json_decode(SimpleGooglePlaces::getDataFromGoogleApis($place_id));
      } catch (Exception $ex) {
        if (variable_get('simple_google_places_log', FALSE)) {
          watchdog_exception(__FUNCTION__, $ex, 'Can not get data for %pid', ['%pid' => $place_id], WATCHDOG_ERROR);
        }
        $data->data = '';
      }
    }
    return $data->data;
  }
  /**
   * Get data from Google Places API.
   *
   * @param string $place_id
   *   The place identifier.
   *
   * @return string
   *   Json data.
   *
   * @throws Exception
   */
  protected static function getDataFromGoogleApis($place_id) {
    $key = variable_get('simple_google_places_api_key', '');
    $url = sprintf('%s?placeid=%s&key=%s',
      self::END_POINT,
      $place_id,
      $key);

    $options = [
      'timeout' => 2,
    ];
    $check = drupal_http_request($url, $options);

    if (empty($check->error)) {
      $data = json_decode($check->data);
      if ($data->status == 'OK') {
        $data = json_decode($check->data);
        drupal_alter('simple_google_places_alter_json', $data);
        cache_set('simple_google_places_' . $place_id, $data, 'cache', REQUEST_TIME + 3600);
        return $check->data;
      }
      else {
        if ($data->status == 'REQUEST_DENIED') {
          throw new Exception(t('Invalid API key'));
        }
        if ($data->status == 'INVALID_REQUEST') {
          throw new Exception(t('Invalid place ID'));
        }
      }
    }
    else {
      throw new Exception(t($check->error));
    }
  }
}