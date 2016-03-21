// -*- C++ -*-
/*!
 * @file  PoseLogger.cpp
 * @brief PoseLogger for VREP Mobile Robot Simulation
 * @date $Date$
 *
 * $Id$
 */

#include "PoseLogger.h"

// Module specification
// <rtc-template block="module_spec">
static const char* poselogger_spec[] =
  {
    "implementation_id", "PoseLogger",
    "type_name",         "PoseLogger",
    "description",       "PoseLogger for VREP Mobile Robot Simulation",
    "version",           "1.0.0",
    "vendor",            "SSR",
    "category",          "Logge",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.debug", "0",
    // Widget
    "conf.__widget__.debug", "text",
    // Constraints
    ""
  };
// </rtc-template>


#include <time.h>
#include <sstream>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PoseLogger::PoseLogger(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_pose2dIn("pose2d", m_pose2d),
    m_pose3dIn("pose3d", m_pose3d)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PoseLogger::~PoseLogger()
{
}



RTC::ReturnCode_t PoseLogger::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("pose2d", m_pose2dIn);
  addInPort("pose3d", m_pose3dIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("debug", m_debug, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PoseLogger::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PoseLogger::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PoseLogger::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t PoseLogger::onActivated(RTC::UniqueId ec_id)
{
	/* åªç›éûçèÇéÊìæ */
	time_t timer = time(NULL);
	struct tm *local = localtime(&timer); /* ínï˚éûÇ…ïœä∑ */

	std::ostringstream oss;
	oss << "pose_log" << local->tm_year + 1900 << local->tm_mon + 1 << local->tm_mday << local->tm_hour << local->tm_min << local->tm_sec << ".log";
	fout.open(oss.str().c_str());
	fout << "pose3d.tm.sec, pose3d.tm.nsec, pose3d.position.x, pose3d.position.y, pose3d.position.z, pose3d.orientation.yaw, pose3d.orientation.roll, pose3d.orientation.pitch, pose2d.tm.sec, pose2d.tm.nsec, pose2d.x, pose2d.y, pose2d.heading\n";

	return RTC::RTC_OK;
}

RTC::ReturnCode_t PoseLogger::onDeactivated(RTC::UniqueId ec_id)
{
	fout.close();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PoseLogger::onExecute(RTC::UniqueId ec_id)
{
	while (m_pose3dIn.isNew()) {
		m_pose3dIn.read();
	}

	while (m_pose2dIn.isNew()) {
		m_pose2dIn.read();
	}

	fout << m_pose3d.tm.sec << ", " << m_pose3d.tm.nsec << ", "
		<< m_pose3d.data.position.x << ", " << m_pose3d.data.position.y << ", " << m_pose3d.data.position.z << ", "
		<< m_pose3d.data.orientation.y << ", " << m_pose3d.data.orientation.p << ", " << m_pose3d.data.orientation.p << ", "
		<< m_pose2d.tm.sec << ", " << m_pose2d.tm.nsec << ", "
		<< m_pose2d.data.position.x << ", " << m_pose2d.data.position.y << ", " << m_pose2d.data.heading << "\n";


	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PoseLogger::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PoseLogger::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PoseLogger::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PoseLogger::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PoseLogger::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void PoseLoggerInit(RTC::Manager* manager)
  {
    coil::Properties profile(poselogger_spec);
    manager->registerFactory(profile,
                             RTC::Create<PoseLogger>,
                             RTC::Delete<PoseLogger>);
  }
  
};


