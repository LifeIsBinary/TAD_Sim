// 获取 configKey 对应的权限值
export function getPermission (configKey) {
  return window.electron.getPermission(configKey)
}
