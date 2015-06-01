package mooc.vandy.weatherserviceapp;

import android.os.Parcel;
import android.os.Parcelable;

/**
 * This class is a Plain Old Java Object (POJO) used for data
 * transport within the WeatherService app.  This POJO implements the
 * Parcelable interface to enable IPC between the WeatherActivity and
 * the WeatherServiceSync and WeatherServiceAsync. It represents the
 * response Json obtained from the Open Weather Map API, e.g., a call
 * to http://api.openweathermap.org/data/2.5/weather?q=Nashville,TN
 * might return the following Json data:
 * <p/>
 * { "coord":{ "lon":-86.78, "lat":36.17 }, "sys":{ "message":0.0138,
 * "country":"United States of America", "sunrise":1431427373,
 * "sunset":1431477841 }, "weather":[ { "id":802, "main":"Clouds",
 * "description":"scattered clouds", "icon":"03d" } ],
 * "base":"stations", "main":{ "temp":289.847, "temp_min":289.847,
 * "temp_max":289.847, "pressure":1010.71, "sea_level":1035.76,
 * "grnd_level":1010.71, "humidity":76 }, "wind":{ "speed":2.42,
 * "deg":310.002 }, "clouds":{ "all":36 }, "dt":1431435983,
 * "id":4644585, "name":"Nashville", "cod":200 }
 * <p/>
 * The meaning of these Json fields is documented at
 * http://openweathermap.org/weather-data#current.
 * <p/>
 * Parcelable defines an interface for marshaling/de-marshaling
 * https://en.wikipedia.org/wiki/Marshalling_(computer_science)
 * to/from a format that Android uses to allow data transport between
 * processes on a device.  Discussion of the details of Parcelable is
 * outside the scope of this assignment, but you can read more at
 * https://developer.android.com/reference/android/os/Parcelable.html.
 */
public class WeatherData implements Parcelable
{
  /**
   * public Parcelable.Creator for WeatherData, which is an
   * interface that must be implemented and provided as a public
   * CREATOR field that generates instances of your Parcelable class
   * from a Parcel.
   */
  public static final Creator<WeatherData> CREATOR =
    new Creator<WeatherData>()
    {
      public WeatherData createFromParcel(Parcel in)
      {
        return new WeatherData(in);
      }

      public WeatherData[] newArray(int size)
      {
        return new WeatherData[size];
      }
    };

  /*
   * These data members are the local variables that will store the
   * WeatherData's state
   */
  private String mName;
  private double mSpeed;
  private double mDeg;
  private double mTemp;
  private long mHumidity;
  private long mSunrise;
  private long mSunset;

  /**
   * Constructor
   *
   * @param name     The name.
   * @param speed    The speed.
   * @param deg      The degrees temperature.
   * @param temp     The temperature.
   * @param humidity The humidity.
   * @param sunrise  The sunrise
   * @param sunset   The sunset.
   */
  public WeatherData(String name,
                     double speed,
                     double deg,
                     double temp,
                     long humidity,
                     long sunrise,
                     long sunset)
  {
    mName = name;
    mSpeed = speed;
    mDeg = deg;
    mTemp = temp;
    mHumidity = humidity;
    mSunrise = sunrise;
    mSunset = sunset;
  }

    /*
     * BELOW THIS is related to Parcelable Interface.
     */

  /**
   * Private constructor provided for the CREATOR interface, which
   * is used to de-marshal an WeatherData from the Parcel of data.
   * <p/>
   * The order of reading in variables HAS TO MATCH the order in
   * writeToParcel(Parcel, int)
   *
   * @param in Input data.
   */
  private WeatherData(Parcel in)
  {
    mName = in.readString();
    mSpeed = in.readDouble();
    mDeg = in.readDouble();
    mTemp = in.readDouble();
    mHumidity = in.readLong();
    mSunrise = in.readLong();
    mSunset = in.readLong();
  }

  /**
   * Provides a printable representation of this object.
   */
  @Override
  public String toString()
  {
    return "WeatherData [name=" + mName
      + ", speed=" + mSpeed
      + ", deg=" + mDeg
      + ", temp=" + mTemp
      + ", humidity=" + mHumidity
      + ", sunrise=" + mSunrise
      + ", sunset=" + mSunset + "]";
  }

  /**
   * A bitmask indicating the set of special object types marshaled
   * by the Parcelable.
   */
  @Override
  public int describeContents()
  {
    return 0;
  }

  /**
   * Write this instance out to byte contiguous memory.
   */
  @Override
  public void writeToParcel(Parcel dest, int flags)
  {
    dest.writeString(mName);
    dest.writeDouble(mSpeed);
    dest.writeDouble(mDeg);
    dest.writeDouble(mTemp);
    dest.writeLong(mHumidity);
    dest.writeLong(mSunrise);
    dest.writeLong(mSunset);
  }

  public String getName()
  {
    return mName;
  }

  public double getSpeed()
  {
    return mSpeed;
  }

  public double getDeg()
  {
    return mDeg;
  }

  public double getTemp()
  {
    return mTemp;
  }

  public long getHumidity()
  {
    return mHumidity;
  }

  public long getSunrise()
  {
    return mSunrise;
  }

  public long getSunset()
  {
    return mSunset;
  }
}
