function default-eosio-directories() {
  # Handles choosing which EOSIO directory to select when the default location is used.
  ALL_EOSIO_SUBDIRS=($(echo $(ls ${HOME}/eosio)))
  PROMPT_EOSIO_DIRS=()
  for ITEM in "${ALL_EOSIO_SUBDIRS[@]}"; do
    if [[ "$ITEM" > "$EOSIO_MIN_VERSION" && "$ITEM" < "$EOSIO_MAX_VERSION" ]]; then
      PROMPT_EOSIO_DIRS+=($ITEM)
    fi
  done
  CONTINUE=true
  if [[ $NONINTERACTIVE != true ]]; then
    while $CONTINUE -eq true; do
      echo "We detected the following items in the default EOSIO path:"
      printf '%s\n' "${PROMPT_EOSIO_DIRS[@]}"
      printf "Enter the EOSIO version number/directory to use:" && read -p " " EOSIO_VERSION
      for ITEM in "${PROMPT_EOSIO_DIRS[@]}"; do
        if [[ "$ITEM" = "$EOSIO_VERSION" ]]; then
          CONTINUE=false
        fi
      done
    done
  else
    REGEX='^[0-9]+([.][0-9]+)?$'
    for ITEM in "${PROMPT_EOSIO_DIRS[@]}"; do
      if [[ "$ITEM" =~ $REGEX ]]; then
        EOSIO_VERSION=$ITEM
      fi
    done
  fi
}


function eosio-version-check() {
  # TODO: Better version comparison. Cut anything off second period, even if doesn't exist. Supports 1.7.x format.
  INSTALLED_VERSION=$(echo $($EOSIO_INSTALL_DIR/bin/nodeos --version) | cut -f1,2 -d '.' | sed 's/v//g' )
  if [[ -z $INSTALLED_VERSION ]]; then
    echo "Could not determine EOSIO version. Exiting..."
    exit 1;
  elif [[ $INSTALLED_VERSION < $EOSIO_MIN_VERSION || $INSTALLED_VERSION > $EOSIO_MAX_VERSION ]]; then 
    echo "Detected unsupported EOSIO version $INSTALLED_VERSION. Versions supported are from $EOSIO_MIN_VERSION to $EOSIO_MAX_VERSION."
    exit 1;
  elif [[ $INSTALLED_VERSION > $EOSIO_SOFT_MAX_VERSION ]]; then
    echo "Detected EOSIO version is greater than recommand max of $EOSIO_SOFT_MAX_VERSION. Proceed with caution."
  fi
  echo "Using EOSIO installation at: $EOSIO_INSTALL_DIR"
  echo "Using EOSIO.CDT installation at: $CDT_INSTALL_DIR"
  export CMAKE_PREFIX_PATH="${EOSIO_INSTALL_DIR};${CDT_INSTALL_DIR}"
  echo $CMAKE_PREFIX_PATH
}


function eosio-directory-prompt() {
  # Handles prompts and default behavior for choosing EOSIO directory.
  if [[ -z $EOSIO_DIR_PROMPT ]]; then
    echo 'No EOSIO location was specified.'
    while true; do
      if [[ $NONINTERACTIVE != true ]]; then
        printf "Is EOSIO installed in the default location: $HOME/eosio/X.Y (y/n)" && read -p " " PROCEED
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


function cdt-directory-prompt() {
  # Handles prompts and default behavior for choosing EOSIO.CDT directory.
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