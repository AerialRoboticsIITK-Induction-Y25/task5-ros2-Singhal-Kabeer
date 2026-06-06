from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # 1. Alpha Drone
        Node(
            package='drone-fleet',
            executable='drone_node',
            name='alpha_drone',
            output='screen',
            parameters=[{
                'drone_name': 'alpha',
                'initial_battery': 100.0,
                'mission_name': 'recon_alpha'
            }]
        ),
        
        # 2. Beta Drone
        Node(
            package='drone-fleet',
            executable='drone_node',
            name='beta_drone',
            output='screen',
            parameters=[{
                'drone_name': 'beta',
                'initial_battery': 60.0,
                'mission_name': 'recon_beta'
            }]
        ),
        
        # 3. Gamma Drone (Starts nearly critical)
        Node(
            package='drone-fleet',
            executable='drone_node',
            name='gamma_drone',
            output='screen',
            parameters=[{
                'drone_name': 'gamma',
                'initial_battery': 35.0,
                'mission_name': 'recon_gamma'
            }]
        ),
        
        # 4. Fleet Manager
        Node(
            package='drone-fleet',
            executable='fleet_manager',
            name='fleet_manager_node',
            output='screen'
        ),

        
        # 5. Health Monitor (Included for completeness based on specs)
        Node(
            package='drone-fleet',
            executable='health_monitor',
            name='health_monitor_node',
            output='screen'
        )
    ])