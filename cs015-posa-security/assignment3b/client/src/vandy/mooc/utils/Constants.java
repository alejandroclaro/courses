package vandy.mooc.utils;

/**
 * Class that contains all the Constants required in our Video Upload client
 * App.
 */
public class Constants
{
  /**
   * URL of the VideoWebService. Please Read the Instructions in README.md to
   * set up the SERVER_URL.
   */
  public static final String SERVER_URL = "https://10.0.2.2:8443";

  /**
   * Define a constant for 1 MB.
   */
  public static final long MEGA_BYTE = 1024 * 1024;

  /**
   * Maximum size of Video to be uploaded in MB.
   */
  public static final long MAX_SIZE_MEGA_BYTE = 50 * MEGA_BYTE;

  public static final String CLIENT_ID = "mobile";

  public static final String TOKEN_PATH = "/oauth/token";
}
