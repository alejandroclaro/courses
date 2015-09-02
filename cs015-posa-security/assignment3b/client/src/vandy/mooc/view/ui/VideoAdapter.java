package vandy.mooc.view.ui;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.List;

import vandy.mooc.R;
import vandy.mooc.model.mediator.webdata.Video;
import vandy.mooc.presenter.VideoOps;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.TextView;
import android.widget.ToggleButton;

public class VideoAdapter extends BaseAdapter
{
  private final Context           mContext;
  private WeakReference<VideoOps> mOps;
  private List<Video>             mVideoList = new ArrayList<Video>();

  public VideoAdapter(Context context, VideoOps ops)
  {
    super();
    mContext = context;
    mOps = new WeakReference<VideoOps>(ops);
  }

  public View getView(int position, View convertView, ViewGroup parent)
  {
    final Video video = mVideoList.get(position);

    if (convertView == null)
    {
      LayoutInflater mInflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
      convertView = mInflater.inflate(R.layout.video_list_item, null);
    }

    TextView titleText = (TextView) convertView.findViewById(R.id.tvVideoTitle);
    TextView likesText = (TextView) convertView.findViewById(R.id.tvVideoLikes);
    titleText.setText(video.getName());
    likesText.setText(Long.toString(video.getLikes()));

    ToggleButton likeToggle = (ToggleButton) convertView.findViewById(R.id.tvVideoToggle);
    likeToggle.setChecked(mOps.get().likeIt(video));

    likeToggle.setOnCheckedChangeListener(new OnCheckedChangeListener()
    {
      public void onCheckedChanged(CompoundButton buttonView, boolean isChecked)
      {
        if (isChecked)
        {
          Log.d("VideoAdapter", "like");
          mOps.get().like(video);
        }
        else
        {
          Log.d("VideoAdapter", "unlike");
          mOps.get().unlike(video);
        }

        mOps.get().getVideoList();
      }
    });

    return convertView;
  }

  public void add(Video video)
  {
    mVideoList.add(video);
    notifyDataSetChanged();
  }

  public void remove(Video video)
  {
    mVideoList.remove(video);
    notifyDataSetChanged();
  }

  public List<Video> getVideos()
  {
    return mVideoList;
  }

  public void setVideos(List<Video> videos)
  {
    this.mVideoList = videos;
    notifyDataSetChanged();
  }

  public int getCount()
  {
    return mVideoList.size();
  }

  public Video getItem(int position)
  {
    return mVideoList.get(position);
  }

  public long getItemId(int position)
  {
    return position;
  }
}
