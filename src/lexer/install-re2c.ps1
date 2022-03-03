if ($IsWindows) {
    choco install -y re2c
}
elseif ($IsLinux -or $IsMacOS) {
    brew install re2c
}
else {
    Throw "Unknown platform"
}