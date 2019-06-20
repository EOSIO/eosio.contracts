# Ensures passed in version values are supported.
function version-check() {
  CHECK_VERSION_MAJOR=$1
  CHECK_VERSION_MINOR=$2
  VALID_VERSION=1

  # Installed major between min and max major.
  if [[ $CHECK_VERSION_MAJOR -gt $EOSIO_MIN_VERSION_MAJOR && $CHECK_VERSION_MAJOR -lt $EOSIO_MAX_VERSION_MAJOR ]]; then
    VALID_VERSION=0
  # Installed major same as minimum major. Check if minor is greater.
  elif [[ $CHECK_VERSION_MAJOR -eq $EOSIO_MIN_VERSION_MAJOR && $CHECK_VERSION_MAJOR -lt $EOSIO_MAX_VERSION_MAJOR ]]; then
    if [[ $CHECK_VERSION_MINOR -ge $EOSIO_MIN_VERSION_MINOR ]]; then
      VALID_VERSION=0
    fi
  # Installed major same as maximum major. Check if minor is less.
  elif [[ $CHECK_VERSION_MAJOR -eq $EOSIO_MAX_VERSION_MAJOR && $CHECK_VERSION_MAJOR -gt $EOSIO_MIN_VERSION_MAJOR ]]; then
    if [[ $CHECK_VERSION_MINOR -le $EOSIO_MAX_VERSION_MINOR ]]; then
      VALID_VERSION=0
    fi
  # Installed major same as both. Ensure minor is between both.
  else
    if [[ $CHECK_VERSION_MINOR -ge $EOSIO_MIN_VERSION_MINOR && $CHECK_VERSION_MINOR -le $EOSIO_MAX_VERSION_MINOR ]]; then
      VALID_VERSION=0
    fi
  fi
  exit $VALID_VERSION
}


# Handles choosing which EOSIO directory to select when the default location is used.
function default-eosio-directories() {
  REGEX='^[0-9]+([.][0-9]+)?$'
  ALL_EOSIO_SUBDIRS=($(ls ${HOME}/eosio))
  CONTINUE=true

  for ITEM in "${ALL_EOSIO_SUBDIRS[@]}"; do
    if [[ "$ITEM" =~ $REGEX ]]; then
      DIR_MAJOR=$(echo $ITEM | cut -f1 -d '.')
      DIR_MINOR=$(echo $ITEM | cut -f2 -d '.')
      if $(version-check $DIR_MAJOR $DIR_MINOR); then
        PROMPT_EOSIO_DIRS+=($ITEM)
      fi
    fi
  done

  if [[ $NONINTERACTIVE != true ]]; then
    while $CONTINUE -eq true; do
      echo "The following installations are compatible in the default EOSIO path:"
      printf '%s\n' "${PROMPT_EOSIO_DIRS[@]}"
      printf "Enter the EOSIO version number/directory to use:" && read -p " " EOSIO_VERSION
      for ITEM in "${PROMPT_EOSIO_DIRS[@]}"; do
        if [[ "$ITEM" = "$EOSIO_VERSION" ]]; then
          CONTINUE=false
        fi
      done
    done
  else
    for ITEM in "${ALL_EOSIO_SUBDIRS[@]}"; do
      if [[ "$ITEM" =~ $REGEX ]]; then
        EOSIO_VERSION=$ITEM
      fi
    done
  fi
}


# Prompts or sets default behavior for choosing EOSIO directory.
function eosio-directory-prompt() {
  if [[ -z $EOSIO_DIR_PROMPT ]]; then
    echo 'No EOSIO location was specified.'
    while true; do
      if [[ $NONINTERACTIVE != true ]]; then
        printf "Is EOSIO installed in a default location: $HOME/eosio/X.Y (y/n)" && read -p " " PROCEED
      fi
      echo ""
      case $PROCEED in
        "" )
          echo "Is EOSIO installed in the default location?";;
        0 | true | [Yy]* )
          default-eosio-directories;
          break;;
        1 | false | [Nn]* )
          printf "Enter the installation location of EOSIO:" && read -p " " EOSIO_DIR_PROMPT;
          break;;
        * )
          echo "Please type 'y' for yes or 'n' for no.";;
      esac
    done
  fi
  export EOSIO_INSTALL_DIR="${EOSIO_DIR_PROMPT:-${HOME}/eosio/${EOSIO_VERSION}}"
}


# Prompts or default behavior for choosing EOSIO.CDT directory.
function cdt-directory-prompt() {
  if [[ -z $CDT_DIR_PROMPT ]]; then
    echo 'No EOSIO.CDT location was specified.'
    while true; do
      if [[ $NONINTERACTIVE != true ]]; then
        printf "Is EOSIO.CDT installed in the default location? /usr/local/eosio.cdt (y/n)" && read -p " " PROCEED
      fi
      echo ""
      case $PROCEED in
        "" )
          echo "Is EOSIO.CDT installed in the default location?";;
        0 | true | [Yy]* )
          break;;
        1 | false | [Nn]* )
          printf "Enter the installation location of EOSIO.CDT:" && read -p " " CDT_DIR_PROMPT;
          break;;
        * )
          echo "Please type 'y' for yes or 'n' for no.";;
      esac
    done
  fi
  export CDT_INSTALL_DIR="${CDT_DIR_PROMPT:-/usr/local/eosio.cdt}"
}


# Ensures EOSIO is installed and compatible via version listed in tests/CMakeLists.txt.
function eosio-version-check() {
  INSTALLED_VERSION_MAJOR=$(echo $($EOSIO_INSTALL_DIR/bin/nodeos --version) | cut -f1 -d '.' | sed 's/v//g' )
  INSTALLED_VERSION_MINOR=$(echo $($EOSIO_INSTALL_DIR/bin/nodeos --version) | cut -f2 -d '.' | sed 's/v//g' )

  if [[ -z $INSTALLED_VERSION_MAJOR || -z $INSTALLED_VERSION_MINOR ]]; then
    echo "Could not determine EOSIO version. Exiting..."
    exit 1;
  fi

  if $(version-check $INSTALLED_VERSION_MAJOR $INSTALLED_VERSION_MINOR); then
    if [[ $INSTALLED_VERSION_MINOR -gt $EOSIO_SOFT_MAX_MINOR || $INSTALLED_VERSION_MAJOR -gt $EOSIO_SOFT_MAX_MAJOR ]]; then
      echo "Detected EOSIO version is greater than recommended soft max: $EOSIO_SOFT_MAX_MAJOR.$EOSIO_SOFT_MAX_MINOR. Proceed with caution."
    fi
    echo "Using EOSIO installation at: $EOSIO_INSTALL_DIR"
    echo "Using EOSIO.CDT installation at: $CDT_INSTALL_DIR"
  else
    echo "Supported versions are: $EOSIO_MIN_VERSION_MAJOR.$EOSIO_MIN_VERSION_MINOR - $EOSIO_MAX_VERSION_MAJOR.$EOSIO_MAX_VERSION_MINOR"
    echo "Invalid EOSIO installation. Exiting..."
    exit 1;
  fi
  export CMAKE_FRAMEWORK_PATH="${EOSIO_INSTALL_DIR}:${CDT_INSTALL_DIR}:${CMAKE_PREFIX_PATH}"
}