// Copyright 2024 Tencent Inc. All rights reserved.
//
// Author: (mama)
//
// 1. 接收到PARKING_STATE的msg不为空,获取到主车处于"泊入状态";
// 2. 根据主车位置获取当前车道,并由此查询当前道路.
// 3. 计算当前道路的坡度,与最大坡度阈值进行比较,并更新"泊车时最大的坡道坡度";
// 4. 最终仿真结束时,输出"泊车时最大的坡道坡度".

#pragma once

#include "eval/eval_base.h"

namespace eval {
class EvalParkingSlope : public EvalBase {
 private:
  /**
   * @brief 用上升沿检测模版类
   */
  RiseUpDetection<double> _detector = MakeRiseUpDetection<double>(-1e6);

  double _parking_slope;

 public:
  /**
   * @brief 指标构造函数
   */
  EvalParkingSlope();
  /**
   * @brief 指标析构函数
   */
  virtual ~EvalParkingSlope() {}

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
   * @brief 指标结果附加信息，评测报告用
   */
  static sim_msg::TestReport_PairData s_parking_slope_pair;
  /**
   * @brief 指标名称定义，在factory中注册时的参数，且与json中"name"一一对应
   */
  static const char _kpi_name[];
  /**
   * @brief  指标Build方法，在factory中注册时传入的方法
   * @return EvalBasePtr 指标指针
   */
  static EvalBasePtr Build() { return std::make_shared<EvalParkingSlope>(); }
};
}  // namespace eval
