/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package cmd

import (
	"github.com/redseverity/cravdata/cmd/validators/urlvalidator"
	"github.com/spf13/cobra"
)

var (
	marker string
)

// urlCmd represents the url command
var urlCmd = &cobra.Command{
	Use: "url [target-url]",
	// Short: "",
	// Long:  ``,
	Args: func(cmd *cobra.Command, args []string) error {
		if err := urlvalidator.RequireMinArgs(cmd, args, 1); err != nil {
			return err
		}

		if err := urlvalidator.ValidateMarker(args[0], cmd); err != nil {
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
	urlCmd.Flags().StringVarP(&marker, "marker", "m", "", "placeholder for inserting generated words")
}
