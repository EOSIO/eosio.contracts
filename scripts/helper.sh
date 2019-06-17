function eosio-directory-prompt() {
  if [[ -z $EOSIO_INSTALL_DIR ]]; then
    echo 'No EOSIO location was specified.'
    while true; do
      if [[ $NONINTERACTIVE != true ]]; then
        printf "Is EOSIO installed in the default location? (y/n)" && read -p " " PROCEED
      fi
      echo ""
      case $PROCEED in
        "" )
          echo "Is EOSIO installed in the default location?";;
        0 | true | [Yy]* )
          # TODO: Determine version number of default EOSIO.
          # TODO: Read expected directories and offer suggestion, or just default to greatest version number.
          break;;
        1 | false | [Nn]* )
          printf "Enter the installation location of EOSIO:" && read -p " " EOSIO_INSTALL_DIR;
          break;;
        * )
          echo "Please type 'y' for yes or 'n' for no.";;
      esac
    done
  fi
  # TODO: Ensure that minimum supported version of EOSIO is installed.
  # TODO: Update appropriate variable in CMAKE files related to EOSIO installation location.
  # . ./scripts/.environment
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
    # TODO: Update appropriate variable in CMAKE files related to EOSIO.CDT installation location.
  fi
  echo $CDT_INSTALL_DIR
}