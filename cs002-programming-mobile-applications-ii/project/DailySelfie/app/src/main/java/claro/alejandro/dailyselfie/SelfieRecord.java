package claro.alejandro.dailyselfie;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Environment;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;

public class SelfieRecord
{
  private String mTitle;
  private Bitmap mImage;

  public SelfieRecord(String title, Bitmap image)
  {
    mTitle = title;
    mImage = image;
  }

  public String getTitle()
  {
    return mTitle;
  }

  public Bitmap getImage()
  {
    return mImage;
  }

  public File getFile()
  {
    return new File(getStorageDirectory(), getTitle());
  }

  public Uri getImageUri()
  {
    return Uri.fromFile(getFile());
  }

  static public File getStorageDirectory()
  {
    File file = Environment.getExternalStoragePublicDirectory("Selfies");

    file.mkdirs();

    return file;
  }

  static public SelfieRecord fromFile(File file) throws FileNotFoundException
  {
    FileInputStream stream = new FileInputStream(file);
    Bitmap          image  = BitmapFactory.decodeStream(stream);

    return new SelfieRecord(file.getName(), image);
  }

  static public void toFile(SelfieRecord selfie) throws FileNotFoundException
  {
    FileOutputStream stream = new FileOutputStream(selfie.getFile());
    selfie.getImage().compress(Bitmap.CompressFormat.PNG, 100, stream);
  }
}
