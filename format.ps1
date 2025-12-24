$files=(git ls-files --exclude-standard);

foreach ($file in $files) {
    if ((get-item $file).Extension -in ".cpp", ".hpp", ".h", ".hpp") {
        &clang-format -i $file
    }
}
