// Copyright 2024 Tencent Inc. All rights reserved.
//
// 第四十五条
// 机动车在道路上行驶不得超过限速标志/标线标明的速度.
// 在没有限速标志/标线的道路上, 机动车不得超过下列最高行驶速度:
// (一) 没有道路中心线的道路, 城市道路为每小时30公里, 公路为每小时40公里;
// (二) 同方向只有1条机动车道的道路, 城市道路为每小时50公里, 公路为每小时70公里.
//
// \par References:
// [1] http://www.gov.cn/zhengce/2020-12/27/content_5574617.htm
//

#pragma once

#include "eval/eval_base.h"

namespace eval {
class EvalRule45 : public EvalBase {
 private:
  bool _cond_on_urban;
  bool _cond_on_motorway;
  bool _cond_no_center_lane;
  bool _cond_only_one_driving_lane;
  double _result_speed_m_s;
  double _threshold_upper_speed_m_s;
  /**
   * @brief 用上升沿检测模版类
   */
  RiseUpDetection<double> _detector = MakeRiseUpDetection<double>(-1e6);

 public:
  /**
   * @brief 指标构造函数
   */
  EvalRule45();
  /**
   * @brief 指标析构函数
   */
  virtual ~EvalRule45() {}

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
   * @brief 指标plot图定义，评测报告用
   */
  static sim_msg::TestReport_XYPlot s_rule45_plot;
  /**
   * @brief 指标结果附加信息，评测报告用
   */
  static sim_msg::TestReport_PairData s_speed_variance_pair;
  /**
   * @brief 指标名称定义，在factory中注册时的参数，且与json中"name"一一对应
   */
  static const char _kpi_name[];
  /**
   * @brief  指标Build方法，在factory中注册时传入的方法
   * @return EvalBasePtr 指标指针
   */
  static EvalBasePtr Build() { return std::make_shared<EvalRule45>(); }
};
}  // namespace eval
