class AddOptoStateToSmartAdaptors < ActiveRecord::Migration[5.1]
  def change
    add_column :smart_adaptors, :opto_state, :boolean
  end
end
