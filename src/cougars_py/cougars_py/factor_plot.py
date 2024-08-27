import matplotlib.pyplot as plt

class Plotter:
    def __init__(self):
        # Initialize data containers
        self.timestamps = []
        self.values = []
        self.pose_keys = []
        self.gps_timestamps = []
        self.gps_values = []
        self.keyed_lines = []
        
        # Create figure and axis
        self.figure, self.ax = plt.subplots()
        
        # Plot lines with colors and transparency
        self.line, = self.ax.plot([], [], 'r-', alpha=0.7)  # Line object for delta measurements
        self.gps_line, = self.ax.plot([], [], 'b-', alpha=0.7)  # Line object for GPS measurements
        
        # Plot circles at each point
        self.delta_scatter = self.ax.scatter([], [], color='red', alpha=0.8, s=500)  # Larger red circles
        self.gps_scatter = self.ax.scatter([], [], color='blue', alpha=0.8)
        
        self.ax.set_xlabel('Time')
        self.ax.set_ylabel('Value')
        self.ax.grid(True)
        
        # Display the initial plot
        plt.ion()  # Interactive mode on
        plt.show()

    def add_delta_measurement(self, value, timestamp, pose_key):
        """Add a new measurement with a specific timestamp and pose_key."""
        self.timestamps.append(timestamp)
        if self.values:
            new_value = self.values[-1] + value
        else:
            new_value = value
        self.values.append(new_value)
        self.pose_keys.append(pose_key)

    def add_measurement(self, value, timestamp, posekey=None):
        """Add a new measurement with a specific timestamp and optionally link to a pose key."""
        self.gps_timestamps.append(timestamp)
        self.gps_values.append(value)
        
        if posekey is not None:
            try:
                idx = self.pose_keys.index(posekey)
                line = self.ax.plot([self.gps_timestamps[-1], self.timestamps[idx]],
                                    [self.gps_values[-1], self.values[idx]], 'g--')[0]
                self.keyed_lines.append(line)
            except ValueError:
                print(f"Pose key {posekey} not found in delta measurements.")

    def update_plot(self):
        """Update the plot with new measurements."""
        self.line.set_data(self.timestamps, self.values)
        self.gps_line.set_data(self.gps_timestamps, self.gps_values)
        
        self.delta_scatter.set_offsets(list(zip(self.timestamps, self.values)))
        self.gps_scatter.set_offsets(list(zip(self.gps_timestamps, self.gps_values)))
        
        for i, (x, y, key) in enumerate(zip(self.timestamps, self.values, self.pose_keys)):
            self.ax.text(x, y, str(key), color='black', ha='center', va='center', fontsize=10, weight='bold')
        
        if len(self.timestamps) > 1:
            self.ax.set_xlim(min(self.timestamps), max(self.timestamps))
        else:
            self.ax.set_xlim(self.timestamps[0] - 1, self.timestamps[0] + 1)
        
        if len(self.values) > 1:
            self.ax.set_ylim(min(self.values) - 1, max(self.values) + 1)
        else:
            self.ax.set_ylim(self.values[0] - 1, self.values[0] + 1)
        
        plt.draw()
        plt.pause(0.1)

    def show(self):
        """Display the plot."""
        plt.show(block=True)

# # Example usage
# plotter = Plotter()

# import time
# for i in range(20):
#     timestamp = i
#     pose_key = i + 100
#     plotter.add_delta_measurement(i, timestamp, pose_key)
#     if i % 2 == 0:
#         plotter.add_measurement(i, timestamp, posekey=pose_key)
#     else:
#         plotter.add_measurement(i, timestamp)
#     plotter.update_plot()
#     time.sleep(1)

# plotter.show()