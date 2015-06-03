package mooc.vandy.weatherserviceapp.services;

import java.io.BufferedInputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import mooc.vandy.weatherserviceapp.WeatherData;
import mooc.vandy.weatherserviceapp.jsonweather.jsonweather.JsonWeather;
import mooc.vandy.weatherserviceapp.jsonweather.jsonweather.Main;
import mooc.vandy.weatherserviceapp.jsonweather.jsonweather.Sys;
import mooc.vandy.weatherserviceapp.jsonweather.jsonweather.WeatherJSONParser;
import mooc.vandy.weatherserviceapp.jsonweather.jsonweather.Wind;

class WeatherServiceUtils
{
  private final static String WEB_SERVICE_URL         = "http://api.openweathermap.org/data/2.5/weather?q=";
  private final static int    CACHE_TIME_MILLISECONDS = (5 * 60 * 1000); // 5 MIN

  private static Map<String, CacheData> mWeatherCache = new HashMap<>();

  static public synchronized List<WeatherData> getResults(String location)
  {
    CacheData cache = mWeatherCache.get(location);

    if (cache == null || System.currentTimeMillis() > (cache.mTime + CACHE_TIME_MILLISECONDS))
    {
      cache = new CacheData();
      cache.mResults = downloadResults(location);
      cache.mTime = System.currentTimeMillis();

      mWeatherCache.put(location, cache);
    }

    return cache.mResults;
  }

  static private List<WeatherData> downloadResults(String location)
  {
    final List<WeatherData> results     = new ArrayList<>();
    List<JsonWeather>       jsonResults = null;

    try
    {
      final URL url = new URL(WEB_SERVICE_URL + location);

      HttpURLConnection connection = (HttpURLConnection)url.openConnection();

      try (InputStream in = new BufferedInputStream(connection.getInputStream()))
      {
        final WeatherJSONParser parser = new WeatherJSONParser();

        jsonResults = parser.parseJsonStream(in);
      }
      finally
      {
        connection.disconnect();
      }
    }
    catch (Exception e)
    {
      e.printStackTrace();
    }

    if (jsonResults != null && jsonResults.size() > 0)
    {
      for (JsonWeather item : jsonResults)
      {
        Wind wind = item.getWind();
        Main main = item.getMain();
        Sys  sys  = item.getSys();

        results.add(new WeatherData(
          item.getName(),
          wind.getSpeed(),
          wind.getDeg(),
          main.getTemp(),
          main.getHumidity(),
          sys.getSunrise(),
          sys.getSunset()));
      }

      return results;
    }

    return null;
  }

  static private class CacheData
  {
    public long              mTime;
    public List<WeatherData> mResults;
  }

  private WeatherServiceUtils()
  {
    throw new AssertionError();
  }
}
