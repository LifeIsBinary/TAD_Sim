// Copyright 2024 Tencent Inc. All rights reserved.
//
// Author: (dongyuanhu)
//
// 排除换道情况下,从主车与车道中心线的横向偏移距离 和车头横向摆角两方面进行车道保持的状态检测.
// 计算步骤:
// 1. 获取主车位置,主车行驶方向.
// 2. 获取车道中心线.
// 3. 计算主车位置到车道中心线的横向偏移距离.
// 4. 计算主车方向与车道中心线方向的夹角.
// 5. 判断横向偏移距离 是否小于 横向偏移距离阈值.
// 6. 判断车头横向摆角 是否小于 车头横向摆角阈值.
// 7. 如果存在超过阈值的情况,保留不通过状态.
// 8. 在10s内如果存在车道id变换的情况,则不记录该不通过状态,否则记录该不通过状态.

#pragma once

#include "eval/eval_base.h"

namespace eval {

class EvalLaneKeeping : public EvalBase {
 private:
  /**
   * @brief 用上升沿检测模版类
   */
  RiseUpDetection<double> _detector_dist = MakeRiseUpDetection<double>(-1e6);
  /**
   * @brief 用上升沿检测模版类
   */
  RiseUpDetection<double> _detector_dir = MakeRiseUpDetection<double>(-1e6);
  bool _record_over_dist;
  bool _record_over_dir;
  double _record_duration;
  double _dist_thresh_value;
  double _dir_thresh_value;

 public:
  /**
   * @brief 指标构造函数
   */
  EvalLaneKeeping();
  /**
   * @brief 指标析构函数
   */
  virtual ~EvalLaneKeeping() {}

 public:
  /**
   * @brief 指标Init方法
   * @param helper 评测辅助类Init类
   * @return true 初始化成功
   * @return false 初始化失败
   */
  virtual bool Init(eval::EvalInit &helper);
  /**
   * @brief 指标Step方法
   * @param helper 评测辅助类Step类
   * @return true 单步执行成功
   * @return false 单步执行失败
   */
  virtual bool Step(eval::EvalStep &helper);
  /**
   * @brief 指标Stop方法
   * @param helper 评测辅助类Stop类
   * @return true 停止成功
   * @return false 停止失败
   */
  virtual bool Stop(eval::EvalStop &helper);

  /**
   * @brief 指标评测结果写入方法
   * @param msg Grading评测消息
   */
  virtual void SetGradingMsg(sim_msg::Grading &msg) override;

  /**
   * @brief 评测通过条件，判断指标是否通过
   * @return EvalResult 判断结果
   */
  virtual EvalResult IsEvalPass();
  /**
   * @brief 结束场景条件，判断指标是否应该立即停止场景
   * @param[out] reason 如果需要终止场景的原因
   * @return true 结束场景
   * @return false 不结束场景
   */
  virtual bool ShouldStopScenario(std::string &reason);

 public:
  /**
   * @brief 指标名称定义，在factory中注册时的参数，且与json中"name"一一对应
   */
  static const char _kpi_name[];
  /**
   * @brief  指标Build方法，在factory中注册时传入的方法
   * @return EvalBasePtr 指标指针
   */
  static EvalBasePtr Build() { return std::make_shared<EvalLaneKeeping>(); }
  /**
   * @brief 指标plot图定义，评测报告用
   */
  static sim_msg::TestReport_XYPlot _s_lane_keeping_plot;
};
}  // namespace eval
