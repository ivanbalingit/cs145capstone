Rails.application.routes.draw do
  post "adaptor/register",  to: "adaptor#register"
  post "adaptor/power_on",  to: "adaptor#power_on"
  post "adaptor/power_off", to: "adaptor#power_off"
  get  "adaptor/get_state", to: "adaptor#get_state"
  get  "adaptor/list",      to: "adaptor#list"
end
