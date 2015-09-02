package org.magnum.mobilecloud.video.repository;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

import com.google.common.base.Objects;

@Entity
public class Video
{
  @Id
  @GeneratedValue(strategy = GenerationType.AUTO)
  private long id;

  private String name;
  private String url;
  private long duration;
  private long likes;

  public Video()
  {
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
    return Objects.hashCode(name, url, duration, likes);
  }

  @Override
  public boolean equals(Object obj)
  {
    if (obj instanceof Video)
    {
      Video other = (Video)obj;
      return Objects.equal(name, other.name) && Objects.equal(url, other.url) && duration == other.duration && likes == other.likes;
    }
    else
    {
      return false;
    }
  }
}
