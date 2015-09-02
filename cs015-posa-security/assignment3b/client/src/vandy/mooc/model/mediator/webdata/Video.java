package vandy.mooc.model.mediator.webdata;

import java.util.Objects;

public class Video
{
  private long id;

  private String name;
  private String url;
  private long duration;
  private long likes;

  public Video()
  {
  }

  public Video(String name, long duration)
  {
    super();
    this.name = name;
    this.duration = duration;
    this.url = "";
    this.likes = 0;
  }

  public Video(String name, String url, long duration, long likes)
  {
    super();
    this.name = name;
    this.url = url;
    this.duration = duration;
    this.likes = likes;
  }

  public String getName()
  {
    return name;
  }

  public void setName(String name)
  {
    this.name = name;
  }

  public String getUrl()
  {
    return url;
  }

  public void setUrl(String url)
  {
    this.url = url;
  }

  public long getDuration()
  {
    return duration;
  }

  public void setDuration(long duration)
  {
    this.duration = duration;
  }

  public long getId()
  {
    return id;
  }

  public void setId(long id)
  {
    this.id = id;
  }

  public long getLikes()
  {
    return likes;
  }

  public void setLikes(long likes)
  {
    this.likes = likes;
  }

  @Override
  public int hashCode()
  {
    return Objects.hash(name, url, duration, likes);
  }

  @Override
  public boolean equals(Object obj)
  {
    if (obj instanceof Video)
    {
      Video other = (Video)obj;
      return Objects.equals(name, other.name) && Objects.equals(url, other.url) && duration == other.duration && likes == other.likes;
    }
    else
    {
      return false;
    }
  }
}
