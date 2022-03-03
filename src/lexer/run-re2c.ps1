Push-Location # Store the current working directory (wherever this script might have been called from)
try {
	Set-Location $PSScriptRoot # Change the working directory to the directory of this script
    re2c --utf-8 --encoding-policy fail lexer.re.cpp -o lexer.cpp
}
finally {
	Pop-Location # Restore the current working directory to whatever it was before this script was called
}