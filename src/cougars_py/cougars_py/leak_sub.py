import rclpy
from rclpy.node import Node
from frost_interfaces.srv import EmergencyStop
from frost_interfaces.msg import LeakStatus
from rclpy.qos import qos_profile_sensor_data


class LeakSubscriber(Node):
    def __init__(self):
        super().__init__("leak_subscriber")

        self.subscription = self.create_subscription(
            LeakStatus, "leak_data", self.listener_callback, qos_profile_sensor_data
        )
        self.subscription  # prevent unused variable warning
        
        self.cli = self.create_client(EmergencyStop, "emergency_stop")
        while not self.cli.wait_for_service(timeout_sec=1):
            self.get_logger().info("EmergencyStop service not available, waiting...")
        self.req = EmergencyStop.Request()

    def send_request(self, err):
        self.req.error = err
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()

    def listener_callback(self, msg):
        if msg.leak:
            error = "ERROR: Leak Detected"
            self.send_request(error)


def main(args=None):
    rclpy.init(args=args)

    leak_subscriber = LeakSubscriber()

    rclpy.spin(leak_subscriber)

    leak_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()