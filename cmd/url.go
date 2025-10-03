/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package cmd

import (
	"fmt"
	"strings"

	"github.com/spf13/cobra"
)

var (
	URL = ""
)

// urlCmd represents the url command
var urlCmd = &cobra.Command{
	Use: "url [URL]",
	// Short: "",
	// Long:  ``,
	Args: func(cmd *cobra.Command, args []string) error {
		var rawURL = args[0]

		// Validate that the command receives at least one argument.
		if err := cobra.MinimumNArgs(1)(cmd, args); err != nil {
			return fmt.Errorf("%s\n ", err.Error())
		}

		//parsing url
		if !strings.HasPrefix(rawURL, "http://") && !strings.HasPrefix(rawURL, "https://") {
			URL = "https://" + rawURL
		}

		return nil
	},

	RunE: func(cmd *cobra.Command, args []string) error {
		return nil
	},
}

func init() {
	rootCmd.AddCommand(urlCmd)
}
