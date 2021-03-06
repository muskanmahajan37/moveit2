/*******************************************************************************
 *      Title     : jog_arm.cpp
 *      Project   : moveit_jog_arm
 *      Created   : 3/9/2017
 *      Author    : Brian O'Neil, Andy Zelenak, Blake Anderson
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2019, Los Alamos National Security, LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#pragma once

#include <memory>

#include <moveit_jog_arm/collision_check.h>
#include <moveit_jog_arm/jog_arm_parameters.h>
#include <moveit_jog_arm/jog_calcs.h>
#include <moveit_jog_arm/joint_state_subscriber.h>

namespace moveit_jog_arm
{
/**
 * Class JogArm - Jacobian based robot control with collision avoidance.
 */
class JogArm
{
public:
  JogArm(ros::NodeHandle& nh, const planning_scene_monitor::PlanningSceneMonitorPtr& planning_scene_monitor);

  ~JogArm();

  /** \brief start jog arm */
  void start();

  /** \brief stop jog arm */
  void stop();

  /** \brief Pause or unpause processing jog commands while keeping the timers alive */
  void setPaused(bool paused);

  /**
   * Get the MoveIt planning link transform.
   * The transform from the MoveIt planning frame to robot_link_command_frame
   *
   * @param transform the transform that will be calculated
   * @return true if a valid transform was available
   */
  bool getCommandFrameTransform(Eigen::Isometry3d& transform);

  /** \brief Get the parameters used by jog arm. */
  const JogArmParameters& getParameters() const;

  /** \brief Get the latest joint state. */
  sensor_msgs::JointStateConstPtr getLatestJointState() const;

private:
  bool readParameters();

  ros::NodeHandle nh_;

  // Pointer to the collision environment
  planning_scene_monitor::PlanningSceneMonitorPtr planning_scene_monitor_;

  // Store the parameters that were read from ROS server
  JogArmParameters parameters_;

  std::shared_ptr<JointStateSubscriber> joint_state_subscriber_;
  std::unique_ptr<JogCalcs> jog_calcs_;
  std::unique_ptr<CollisionCheck> collision_checker_;
};

// JogArmPtr using alias
using JogArmPtr = std::shared_ptr<JogArm>;

}  // namespace moveit_jog_arm
