class AdaptorController < ApplicationController
  # POST adaptor/register
  def register
    if !SmartAdaptor.where(name: params[:name]).first.nil?
      render json: { msg: "ERROR: Adaptor name already used" }
    else
      @a = SmartAdaptor.create(name: params[:name], state: false, opto_state: false)
      render json: { name: @a.name, state: @a.state, opto_state: @a.opto_state, msg: "Adaptor successfully created" }
    end
  end

  # POST adaptor/power_on
  def power_on
    @a = SmartAdaptor.where(name: params[:name]).first
    @a.update(state: true)
    render json: { name: @a.name, state: @a.state, opto_state: @a.opto_state, last_on: @a.last_on, msg: "Adaptor turned on" }
  end

  # POST adaptor/power_off
  def power_off
    @a = SmartAdaptor.where(name: params[:name]).first
    @a.update(state: false)
    render json: { name: @a.name, state: @a.state, opto_state: @a.opto_state, last_on: @a.last_on,  msg: "Adaptor turned off" }
  end

  # GET adaptor/get_state
  def get_state
    @a = SmartAdaptor.where(name: params[:name]).first
    if params[:ard] == "true"
      @a.update(opto_state: params[:opto_state])
      if params[:opto_state] == "true" then @a.update(last_on: Time.now) end
    end
    render json: { name: @a.name, state: @a.state, opto_state: @a.opto_state, last_on: @a.last_on }
  end

  # GET adaptor/list
  def list
    @a_list = []
    SmartAdaptor.all.each { |a| @a_list.append({ name: a.name, state: a.state, opto_state: a.opto_state, last_on: a.last_on }) }
    render json: @a_list
  end
end
