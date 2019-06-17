function default-eosio-directories() {
  EOSIO_DIRECTORIES=("$(echo $(ls ${HOME}/eosio))")
  CONTINUE=true
  if [[ $NONINTERACTIVE != true ]]; then
    while $CONTINUE -eq true; do
      echo "We detected the following directories: ${EOSIO_DIRECTORIES}"
      printf "Enter the EOSIO version number/directory to use:" && read -p " " EOSIO_VERSION
      for ITEM in "${EOSIO_DIRECTORIES[@]}"; do
        if [[ "$ITEM" = "$EOSIO_VERSION" ]]; then
          CONTINUE=false
        fi
      done
    done
  else
    echo "NONINTERACTIVE MODE"
    # TODO: Determine version number of default EOSIO. Max number? First occurance in array?
  fi
}

function eosio-directory-prompt() {
  if [[ -z $EOSIO_INSTALL_DIR ]]; then
    echo 'No EOSIO location was specified.'
    while true; do
      if [[ $NONINTERACTIVE != true ]]; then
        printf "Is EOSIO installed in the default location: $HOME/eosio/ (y/n)" && read -p " " PROCEED
      fi
      echo ""
      case $PROCEED in
        "" )
          echo "Is EOSIO installed in the default location?";;
        0 | true | [Yy]* )
          default-eosio-directories;
          break;;
        1 | false | [Nn]* )
          printf "Enter the installation location of EOSIO:" && read -p " " EOSIO_INSTALL_DIR;
          break;;
        * )
          echo "Please type 'y' for yes or 'n' for no.";;
      esac
    done
  fi
  # TODO: Determine which version of EOSIO is installed. Grep output of command --version?
  # TODO: Ensure that minimum supported version of EOSIO is installed. Compare with tests/CMakeLists.txt.
  # TODO: Update appropriate variables in CMAKE files related to EOSIO installation location.
  # TODO: Test cases of multiple EOSIO installations.
  # TODO: Test custom EOSIO installation.
  . ./scripts/.environment
  echo $EOSIO_INSTALL_DIR
}

function cdt-directory-prompt() {
  if [[ -z $CDT_INSTALL_DIR ]]; then
    echo 'No EOSIO.CDT location was specified.'
    while true; do
      if [[ $NONINTERACTIVE != true ]]; then
        printf "Is EOSIO.CDT installed in the default location? (y/n)" && read -p " " PROCEED
      fi
      echo ""
      case $PROCEED in
        "" )
          echo "Is EOSIO.CDT installed in the default location?";;
        0 | true | [Yy]* )
          CDT_INSTALL_DIR="/usr/local/eosio.cdt";
          break;;
        1 | false | [Nn]* )
          printf "Enter the installation location of EOSIO.CDT:" && read -p " " CDT_INSTALL_DIR;
          break;;
        * )
          echo "Please type 'y' for yes or 'n' for no.";;
      esac
    done
    # TODO: Update appropriate variables in CMAKE files related to EOSIO.CDT installation location.
  fi
  echo $CDT_INSTALL_DIR
}