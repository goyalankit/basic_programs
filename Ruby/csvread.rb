require 'csv'

CSV.foreach("cortac.csv", {:headers => true, col_sep: '|'}) do |row|
  csv = "#{row['key'}"
   puts csv
end
