class AddLastOnToSmartAdaptors < ActiveRecord::Migration[5.1]
  def change
    add_column :smart_adaptors, :last_on, :datetime
  end
end
