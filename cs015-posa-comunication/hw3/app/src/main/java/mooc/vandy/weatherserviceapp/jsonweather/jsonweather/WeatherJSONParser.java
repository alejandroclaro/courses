package mooc.vandy.weatherserviceapp.jsonweather.jsonweather;

import android.util.JsonReader;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

/**
 * Parses the Json weather data returned from the Weather Services API
 * and returns a List of JsonWeather objects that contain this data.
 */
public class WeatherJSONParser
{
  /**
   * Used for logging purposes.
   */
  private final String TAG = this.getClass().getCanonicalName();

  /**
   * Parse the @a inputStream and convert it into a List of JsonWeather
   * objects.
   */
  public List<JsonWeather> parseJsonStream(InputStream inputStream) throws IOException
  {
    // TODO -- you fill in here.
    try (JsonReader reader = new JsonReader(new InputStreamReader(inputStream, "UTF-8")))
    {
      return parseJsonWeatherArray(reader);
    }
  }

  /**
   * Parse a Json stream and convert it into a List of JsonWeather
   * objects.
   */
  public List<JsonWeather> parseJsonWeatherArray(JsonReader reader) throws IOException
  {
    // TODO -- you fill in here.
    List<JsonWeather> result = new ArrayList<>();

    JsonWeather weather = parseJsonWeather(reader);

    if (weather != null && weather.getWind() != null && weather.getMain() != null && weather.getSys() != null)
      result.add(weather);

    return result;
  }

  /**
   * Parse a Json stream and return a JsonWeather object.
   */
  public JsonWeather parseJsonWeather(JsonReader reader) throws IOException
  {
    // TODO -- you fill in here.
    JsonWeather result = new JsonWeather();

    try
    {
      reader.beginObject();

      while (reader.hasNext())
      {
        String name = reader.nextName();

        switch (name)
        {
          case JsonWeather.cod_JSON:
            result.setCod(reader.nextLong());
            break;
          case JsonWeather.name_JSON:
            result.setName(reader.nextString());
            break;
          case JsonWeather.id_JSON:
            result.setId(reader.nextLong());
            break;
          case JsonWeather.dt_JSON:
            result.setDt(reader.nextLong());
            break;
          case JsonWeather.wind_JSON:
            result.setWind(parseWind(reader));
            break;
          case JsonWeather.main_JSON:
            result.setMain(parseMain(reader));
            break;
          case JsonWeather.base_JSON:
            result.setBase(reader.nextString());
            break;
          case JsonWeather.weather_JSON:
            result.setWeather(parseWeathers(reader));
            break;
          case JsonWeather.sys_JSON:
            result.setSys(parseSys(reader));
            break;
          default:
            reader.skipValue();
            break;
        }
      }
    }
    finally
    {
      reader.endObject();
    }

    return result;
  }

  /**
   * Parse a Json stream and return a List of Weather objects.
   */
  public List<Weather> parseWeathers(JsonReader reader) throws IOException
  {
    // TODO -- you fill in here.
    List<Weather> result = new ArrayList<>();

    try
    {
      reader.beginArray();

      while (reader.hasNext())
      {
        Weather weather = parseWeather(reader);

        if (weather != null)
          result.add(weather);
      }
    }
    finally
    {
      reader.endArray();
    }

    return result;
  }

  /**
   * Parse a Json stream and return a Weather object.
   */
  public Weather parseWeather(JsonReader reader) throws IOException
  {
    // TODO -- you fill in here.
    Weather result = new Weather();

    try
    {
      reader.beginObject();

      while (reader.hasNext())
      {
        String name = reader.nextName();

        switch (name)
        {
          case Weather.id_JSON:
            result.setId(reader.nextLong());
            break;
          case Weather.main_JSON:
            result.setMain(reader.nextString());
            break;
          case Weather.description_JSON:
            result.setDescription(reader.nextString());
            break;
          case Weather.icon_JSON:
            result.setIcon(reader.nextString());
            break;
          default:
            reader.skipValue();
            break;
        }
      }
    }
    finally
    {
      reader.endObject();
    }

    return result;
  }

  /**
   * Parse a Json stream and return a Main Object.
   */
  public Main parseMain(JsonReader reader) throws IOException
  {
    // TODO -- you fill in here.
    Main result = new Main();

    try
    {
      reader.beginObject();

      while (reader.hasNext())
      {
        String name = reader.nextName();

        switch (name)
        {
          case Main.temp_JSON:
            result.setTemp(reader.nextDouble());
            break;
          case Main.tempMin_JSON:
            result.setTempMin(reader.nextDouble());
            break;
          case Main.tempMax_JSON:
            result.setTempMax(reader.nextDouble());
            break;
          case Main.pressure_JSON:
            result.setPressure(reader.nextDouble());
            break;
          case Main.seaLevel_JSON:
            result.setSeaLevel(reader.nextDouble());
            break;
          case Main.grndLevel_JSON:
            result.setGrndLevel(reader.nextDouble());
            break;
          case Main.humidity_JSON:
            result.setHumidity(reader.nextLong());
            break;
          default:
            reader.skipValue();
            break;
        }
      }
    }
    finally
    {
      reader.endObject();
    }

    return result;
  }

  /**
   * Parse a Json stream and return a Wind Object.
   */
  public Wind parseWind(JsonReader reader) throws IOException
  {
    // TODO -- you fill in here.
    Wind result = new Wind();

    try
    {
      reader.beginObject();

      while (reader.hasNext())
      {
        String name = reader.nextName();

        switch (name)
        {
          case Wind.deg_JSON:
            result.setDeg(reader.nextDouble());
            break;
          case Wind.speed_JSON:
            result.setSpeed(reader.nextDouble());
            break;
          default:
            reader.skipValue();
            break;
        }
      }
    }
    finally
    {
      reader.endObject();
    }

    return result;
  }

  /**
   * Parse a Json stream and return a Sys Object.
   */
  public Sys parseSys(JsonReader reader) throws IOException
  {
  // TODO -- you fill in here.
    Sys result = new Sys();

    try
    {
      reader.beginObject();

      while (reader.hasNext())
      {
        String name = reader.nextName();

        switch (name)
        {
          case Sys.message_JSON:
            result.setMessage(reader.nextDouble());
            break;
          case Sys.country_JSON:
            result.setCountry(reader.nextString());
            break;
          case Sys.sunrise_JSON:
            result.setSunrise(reader.nextLong());
            break;
          case Sys.sunset_JSON:
            result.setSunset(reader.nextLong());
            break;
          default:
            reader.skipValue();
            break;
        }
      }
    }
    finally
    {
      reader.endObject();
    }

    return result;
  }
}
