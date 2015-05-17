package claro.alejandro.dailyselfie;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;

public class SelfieViewAdapter extends BaseAdapter
{
  private Context mContext;
  private ArrayList<SelfieRecord> mList = new ArrayList<>();

  static class ViewHolder
  {
    TextView  title;
    ImageView image;
  }

  public SelfieViewAdapter(Context context)
  {
    mContext = context;
  }

  public void load()
  {
    File   directory = SelfieRecord.getStorageDirectory();
    File[] files     = directory.listFiles();

    for (File file : files)
    {
      try
      {
        SelfieRecord selfie = SelfieRecord.fromFile(file);
        mList.add(selfie);
      }
      catch (FileNotFoundException e)
      {
        e.printStackTrace();
      }
    }

    notifyDataSetChanged();
  }

  public void add(SelfieRecord item)
  {
    mList.add(item);

    try
    {
      SelfieRecord.toFile(item);
    }
    catch (FileNotFoundException e)
    {
      e.printStackTrace();
    }

    notifyDataSetChanged();
  }

  public void clear()
  {
    for (SelfieRecord selfie : mList)
    {
      selfie.getFile().delete();
    }

    mList.clear();

    notifyDataSetChanged();
  }

  @Override
  public int getCount()
  {
    return mList.size();
  }

  @Override
  public SelfieRecord getItem(int position)
  {
    return mList.get(position);
  }

  @Override
  public long getItemId(int position)
  {
    return position;
  }

  @Override
  public View getView(int position, View convertView, ViewGroup parent)
  {
    View         newView      = convertView;
    SelfieRecord selfieRecord = mList.get(position);
    ViewHolder   holder;

    if (convertView == null)
    {
      holder = new ViewHolder();

      newView      = LayoutInflater.from(mContext).inflate(R.layout.selfie_view, parent, false);
      holder.title = (TextView)newView.findViewById(R.id.selfie_title);
      holder.image = (ImageView)newView.findViewById(R.id.selfie_image);

      newView.setTag(holder);
    }
    else
    {
      holder = (ViewHolder)newView.getTag();
    }

    holder.image.setImageBitmap(selfieRecord.getImage());
    holder.title.setText(selfieRecord.getTitle());

    return newView;
  }
}
