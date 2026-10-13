-module(randomE).
-export([main/0]).

main() ->
    Cantidad = 1000000,

    %% Inicializar el generador de números aleatorios
    rand:seed(exsplus, {erlang:monotonic_time(),
                        erlang:unique_integer(),
                        erlang:phash2(self())}),

    {ok, File} = file:open("randomE_0_1.txt", [write]),

    generar(File, Cantidad),

    file:close(File),
    io:format("Archivo generado correctamente.~n").

generar(_File, 0) ->
    ok;
generar(File, N) ->
    X = rand:uniform(),   %% genera un real en (0,1]
    %% Ajuste para obtener [0,1)
    Y = 1.0 - X,
    io:format(File, "~.16f~n", [Y]),
    generar(File, N - 1).
