if which g++ >/dev/null; then
    echo "g++ is installed"
else
    echo "g++ is not installed"
    echo "Please install g++"
    exit 1
fi

if which make >/dev/null; then
    echo "make is installed"
else
    echo "make is not installed"
    echo "Please install make"
    exit 1
fi

function checklib() {
  echo "int main() { return 0; }" | g++ -x c++ - -l$1 -o tmp.out
  if [ $? -eq 0 ]; then
    echo "$1 is installed"
  else
    echo "$1 is not installed"
    echo "Please install $1"
    exit 1
  fi
}

echo "int main() { return 0; }" | g++ -x c++ - -std=c++17 -o tmp.out
if [ $? -eq 0 ]; then
  echo "g++ supports C++17"
else
  echo "g++ does not support C++17"
  echo "Please install g++ with C++17 support"
  exit 1
fi

checklib(ncursesw)

checklib(panelw)

rm tmp.out

echo "All dependencies are installed"

echo "Installing..."

sudo make install

echo "Done"
echo "Please run 'sudo make uninstall' to uninstall"
echo ""
echo "To run the program, type 'b++' in the terminal"
