$sourceDir = "src"
$destDir = "bin"

New-Item -ItemType Directory -Path bin -Force

Get-ChildItem -Path $sourceDir -Recurse -Directory | ForEach-Object {
    $newDir = $_.FullName.Replace($sourceDir, $destDir)
    New-Item -ItemType Directory -Path $newDir -Force
}