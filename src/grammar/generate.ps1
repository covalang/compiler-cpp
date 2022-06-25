$location = Get-Location
try {
    Set-Location $PSScriptRoot
    java -jar antlr-4.10.1-complete.jar -Dlanguage=Cpp CovaLexer.g4 CovaParser.g4 -o generated
}
finally {
    Set-Location $location
}