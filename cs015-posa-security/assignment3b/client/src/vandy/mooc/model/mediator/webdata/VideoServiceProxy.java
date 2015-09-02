package vandy.mooc.model.mediator.webdata;

import java.util.Collection;

import retrofit.http.Body;
import retrofit.http.GET;
import retrofit.http.POST;
import retrofit.http.Path;

/**
 * This interface defines an API for a Video Service web service. The interface
 * is used to provide a contract for client/server interactions. The interface
 * is annotated with Retrofit annotations to send Requests and automatically
 * convert the Video.
 */
public interface VideoServiceProxy
{
  public static final String ID_PARAMETER = "id";
  public static final String VIDEO_SVC_PATH = "/video";
  public static final String VIDEO_DATA_PATH = VIDEO_SVC_PATH + "/{id}";
  public static final String VIDEO_LIKE_PATH = VIDEO_SVC_PATH + "/{id}/like";
  public static final String VIDEO_UNLIKE_PATH = VIDEO_SVC_PATH + "/{id}/unlike";
  public static final String VIDEO_LIKEDBY_PATH = VIDEO_SVC_PATH + "/{id}/likedby";

  @GET(VIDEO_SVC_PATH)
  public Collection<Video> getVideoList();

  @GET(VIDEO_DATA_PATH)
  public Video getVideoById(@Path("id") long id);

  @POST(VIDEO_SVC_PATH)
  public Video addVideo(@Body Video video);

  @POST(VIDEO_LIKE_PATH)
  public Void like(@Path(ID_PARAMETER) long id, @Body String emptyString);

  @POST(VIDEO_UNLIKE_PATH)
  public Void unlike(@Path(ID_PARAMETER) long id, @Body String emptyString);

  @GET(VIDEO_LIKEDBY_PATH)
  public Collection<String> getLikeBy(@Path(ID_PARAMETER) long id);
}
