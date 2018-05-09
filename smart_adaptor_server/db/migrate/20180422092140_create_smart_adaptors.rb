class CreateSmartAdaptors < ActiveRecord::Migration[5.1]
  def change
    create_table :smart_adaptors do |t|
      t.string :name
      t.boolean :state

      t.timestamps
    end
  end
end
