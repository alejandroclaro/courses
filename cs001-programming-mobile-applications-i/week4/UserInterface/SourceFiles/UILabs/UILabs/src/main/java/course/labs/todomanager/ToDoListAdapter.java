package course.labs.todomanager;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.RelativeLayout;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

public class ToDoListAdapter extends BaseAdapter {

  private static final String TAG = "Lab-UserInterface";
  private final List<ToDoItem> mItems = new ArrayList<ToDoItem>();
  private final Context mContext;

  static class ViewHolder {
    TextView titleView;
    CheckBox statusView;
    TextView priorityView;
    TextView dateView;
    int position;
  }

  public ToDoListAdapter(Context context) {
    mContext = context;
  }

  // Add a ToDoItem to the adapter
  // Notify observers that the data set has changed
  public void add(ToDoItem item) {
    mItems.add(item);
    notifyDataSetChanged();
  }

  // Clears the list adapter of all items.
  public void clear() {
    mItems.clear();
    notifyDataSetChanged();
  }

  // Returns the number of ToDoItems
  @Override
  public int getCount() {
    return mItems.size();
  }

  // Retrieve the number of ToDoItems
  @Override
  public Object getItem(int pos) {
    return mItems.get(pos);
  }

  // Get the ID for the ToDoItem
  // In this case it's just the position
  @Override
  public long getItemId(int pos) {
    return pos;
  }

  // Create a View for the ToDoItem at specified position
  // Remember to check whether convertView holds an already allocated View
  // before created a new View.
  // Consider using the ViewHolder pattern to make scrolling more efficient
  // See: http://developer.android.com/training/improving-layouts/smooth-scrolling.html
  @Override
  public View getView(final int position, View convertView, ViewGroup parent) {
    ViewHolder holder;

    if(convertView == null) {
      // TODO - Inflate the View for this ToDoItem
      // from todo_item.xml
      LayoutInflater inflater = (LayoutInflater)mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
      convertView = inflater.inflate(R.layout.todo_item, parent, false);

      holder = new ViewHolder();

      holder.titleView    = (TextView)convertView.findViewById(R.id.titleView);
      holder.statusView   = (CheckBox)convertView.findViewById(R.id.statusCheckBox);
      holder.priorityView = (TextView)convertView.findViewById(R.id.priorityView);
      holder.dateView     = (TextView)convertView.findViewById(R.id.dateView);
      holder.position     = position;

      holder.statusView.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView,
                                     boolean isChecked) {
          Log.i(TAG, "Entered onCheckedChanged()");
          // TODO - set up an OnCheckedChangeListener, which
          // is called when the user toggles the status checkbox
          mItems.get(position).setStatus(isChecked ? ToDoItem.Status.DONE : ToDoItem.Status.NOTDONE);
        }
      });

      convertView.setTag(holder);
    } else {
      holder = (ViewHolder)convertView.getTag();
    }

    // TODO - Get the current ToDoItem
    final ToDoItem toDoItem = mItems.get(position);

    // TODO - Fill in specific ToDoItem data
    // Remember that the data that goes in this View
    // corresponds to the user interface elements defined
    // in the layout file

    // TODO - Display Title in TextView
    holder.titleView.setText(toDoItem.getTitle());

    // TODO - Set up Status CheckBox
    holder.statusView.setChecked(toDoItem.getStatus() == ToDoItem.Status.DONE);

    // TODO - Display Priority in a TextView
    holder.priorityView.setText(toDoItem.getPriority().toString());

    // TODO - Display Time and Date.
    // Hint - use ToDoItem.FORMAT.format(toDoItem.getDate()) to get date and
    // time String
    holder.dateView.setText(ToDoItem.FORMAT.format(toDoItem.getDate()));

    // Return the View you just created
    return convertView;
  }
}
