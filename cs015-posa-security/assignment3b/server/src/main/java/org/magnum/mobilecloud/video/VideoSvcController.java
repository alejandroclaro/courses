package org.magnum.mobilecloud.video;

import java.security.Principal;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import org.magnum.mobilecloud.video.repository.Video;
import org.magnum.mobilecloud.video.repository.VideoRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import com.google.common.collect.Lists;

@Controller
public class VideoSvcController
{
  public static final String ID_PARAMETER = "id";
  public static final String VIDEO_SVC_PATH = "/video";
  public static final String VIDEO_DATA_PATH = VIDEO_SVC_PATH + "/{id}";
  public static final String VIDEO_LIKE_PATH = VIDEO_SVC_PATH + "/{id}/like";
  public static final String VIDEO_UNLIKE_PATH = VIDEO_SVC_PATH + "/{id}/unlike";
  public static final String VIDEO_LIKEDBY_PATH = VIDEO_SVC_PATH + "/{id}/likedby";

  @Autowired
  private VideoRepository mVideos;
  private Map<Long, List<String>> mVideoUsers = new TreeMap<>();

  @RequestMapping(value = VIDEO_SVC_PATH, method = RequestMethod.GET)
  public @ResponseBody Collection<Video> getVideoList(Principal p)
  {
    return Lists.newArrayList(mVideos.findAll());
  }

  @RequestMapping(value = VIDEO_SVC_PATH, method = RequestMethod.POST)
  public @ResponseBody Video addVideo(@RequestBody Video v, Principal p)
  {
    Video video = mVideos.save(v);

    mVideoUsers.put(video.getId(), new ArrayList<String>());
    return video;
  }

  @RequestMapping(value = VIDEO_DATA_PATH, method = RequestMethod.GET)
  public ResponseEntity<Video> getVideo(@PathVariable(ID_PARAMETER) long id, Principal p)
  {
    Video video = mVideos.findOne(id);

    if (video == null)
      return new ResponseEntity<Video>(HttpStatus.NOT_FOUND);

    return new ResponseEntity<Video>(video, HttpStatus.OK);
  }

  @RequestMapping(value = VIDEO_LIKE_PATH, method = RequestMethod.POST)
  public ResponseEntity<Void> like(@PathVariable(ID_PARAMETER) long id, Principal p)
  {
    Video video = mVideos.findOne(id);

    if (video == null)
      return new ResponseEntity<Void>(HttpStatus.NOT_FOUND);

    if (hasUserLikeIt(id, p.getName()))
      return new ResponseEntity<Void>(HttpStatus.BAD_REQUEST);

    video.setLikes(video.getLikes() + 1);
    mVideos.save(video);
    addUserLike(id, p.getName());

    return new ResponseEntity<Void>(HttpStatus.OK);
  }

  @RequestMapping(value = VIDEO_UNLIKE_PATH, method = RequestMethod.POST)
  public ResponseEntity<Void> unlike(@PathVariable(ID_PARAMETER) long id, Principal p)
  {
    Video video = mVideos.findOne(id);

    if (video == null)
      return new ResponseEntity<Void>(HttpStatus.NOT_FOUND);

    if (hasUserLikeIt(id, p.getName()) == false)
      return new ResponseEntity<Void>(HttpStatus.BAD_REQUEST);

    video.setLikes(video.getLikes() - 1);
    mVideos.save(video);
    removeUserLike(id, p.getName());

    return new ResponseEntity<Void>(HttpStatus.OK);
  }

  @RequestMapping(value = VIDEO_LIKEDBY_PATH, method = RequestMethod.GET)
  public ResponseEntity<Collection<String>> getLikeBy(@PathVariable(ID_PARAMETER) long id, Principal p)
  {
    if (mVideos.exists(id) == false)
      return new ResponseEntity<Collection<String>>(HttpStatus.NOT_FOUND);

    return new ResponseEntity<Collection<String>>(mVideoUsers.get(id), HttpStatus.OK);
  }

  private boolean hasUserLikeIt(long id, String name)
  {
    List<String> users = mVideoUsers.get(id);
    assert(users != null);

    return users.contains(name);
  }

  private void addUserLike(long id, String name)
  {
    List<String> users = mVideoUsers.get(id);
    assert(users != null);

    users.add(name);
  }

  private void removeUserLike(long id, String name)
  {
    List<String> users = mVideoUsers.get(id);
    assert(users != null);

    users.remove(name);
  }
}
