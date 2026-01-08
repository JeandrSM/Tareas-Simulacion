CANTIDAD = 1_000_000
archivo = "randomRuby_0_1.txt"

File.open(archivo, "w") do |file|
  CANTIDAD.times do
    x = rand      # [0.0, 1.0)
    file.puts x
  end
end

puts "Archivo generado correctamente."
