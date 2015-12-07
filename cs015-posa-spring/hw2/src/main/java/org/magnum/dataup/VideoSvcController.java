/*
 *
 * Copyright 2014 Jules White
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
package org.magnum.dataup;

import java.io.IOException;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicLong;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.magnum.dataup.model.Video;
import org.magnum.dataup.model.VideoStatus;
import org.magnum.dataup.model.VideoStatus.VideoState;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.context.request.RequestContextHolder;
import org.springframework.web.context.request.ServletRequestAttributes;
import org.springframework.web.multipart.MultipartFile;

@Controller
public class VideoSvcController
{
  public static final String VIDEO_SVC_PATH = "/video";
  public static final String VIDEO_DATA_PATH = VIDEO_SVC_PATH + "/{id}/data";

  private static final AtomicLong mNextId = new AtomicLong(0L);
  private Map<Long, Video>        mVideos = new HashMap<>();
  private VideoFileManager        mFileManager;

  VideoSvcController() throws IOException
  {
    mFileManager = VideoFileManager.get();
  }

  @RequestMapping(value=VIDEO_SVC_PATH, method=RequestMethod.GET)
  public @ResponseBody Collection<Video> getVideoList()
  {
    return mVideos.values();
  }

  @RequestMapping(value=VIDEO_SVC_PATH, method=RequestMethod.POST)
  public @ResponseBody Video addVideo(@RequestBody Video v)
  {
    checkAndSetId(v);

    v.setDataUrl(getDataUrl(v.getId()));
    mVideos.put(v.getId(), v);

    return v;
  }

  @RequestMapping(value=VIDEO_DATA_PATH, method=RequestMethod.GET)
  public void getData(@PathVariable("id") long id, HttpServletResponse response)
  {
    Video video = mVideos.get(id);

    try
    {
      if (video == null)
      {
        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
      }
      else
      {
        response.setContentType("video/mpeg");
        mFileManager.copyVideoData(video, response.getOutputStream());
      }
    }
    catch (IOException e)
    {
      e.printStackTrace();
      response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
    }
  }

  @RequestMapping(value=VIDEO_DATA_PATH, method=RequestMethod.POST)
  public ResponseEntity<VideoStatus> setVideoData(@PathVariable("id") long id, @RequestParam("data") MultipartFile videoData)
  {
    Video video = mVideos.get(id);

    try
    {
      if (video == null)
      {
        return new ResponseEntity<VideoStatus>(HttpStatus.NOT_FOUND);
      }
      else
      {
        mFileManager.saveVideoData(video, videoData.getInputStream());
        return new ResponseEntity<VideoStatus>(new VideoStatus(VideoState.READY), HttpStatus.OK);
      }
    }
    catch (IOException e)
    {
      e.printStackTrace();
      return new ResponseEntity<VideoStatus>(HttpStatus.INTERNAL_SERVER_ERROR);
    }
  }

  private void checkAndSetId(Video entity)
  {
    if(entity.getId() == 0)
      entity.setId(mNextId.incrementAndGet());
  }

  private String getDataUrl(long id)
  {
    String url = getUrlBaseForLocalServer() + "/video/" + id + "/data";
    return url;
  }

  private String getUrlBaseForLocalServer()
  {
    HttpServletRequest request = ((ServletRequestAttributes)RequestContextHolder.getRequestAttributes()).getRequest();
    String base = "http://" + request.getServerName() + ((request.getServerPort() != 80) ? ":"+request.getServerPort() : "");

    return base;
  }
}
