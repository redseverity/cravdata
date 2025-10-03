/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package cmd

import (
	"github.com/redseverity/cravdata/cmd/validators/urlcheck"
	"github.com/spf13/cobra"
)

// urlCmd represents the url command
var urlCmd = &cobra.Command{
	Use: "url [target-url]",
	// Short: "",
	// Long:  ``,
	Args: func(cmd *cobra.Command, args []string) error {
		if err := urlcheck.RequireMinArgs(cmd, args, 1); err != nil {
			return err
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
